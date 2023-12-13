/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <string_view>

#include <array>

#include <stdexcept>

#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../types.hxx"

namespace ztd::shell
{
class Execute
{
  public:
    Execute() = delete;

    Execute(const std::string_view command)
    {
        if (pipe(this->infd.data()) == -1)
        {
            throw std::runtime_error(std::strerror(errno));
        }

        if (pipe(this->outfd.data()) == -1)
        {
            throw std::runtime_error(std::strerror(errno));
        }

        if (pipe(this->errfd.data()) == -1)
        {
            throw std::runtime_error(std::strerror(errno));
        }

        const pid_t pid = fork();
        if (pid > 0) // PARENT
        {
            close(this->infd[READ_END]);   // Parent does not read from stdin
            close(this->outfd[WRITE_END]); // Parent does not write to stdout
            close(this->errfd[WRITE_END]); // Parent does not write to stderr

            if (write(this->infd[WRITE_END], this->in.data(), this->in.size()) < 0)
            {
                throw std::runtime_error(std::strerror(errno));
            }
            close(this->infd[WRITE_END]); // Done writing
        }
        else if (pid == 0) // CHILD
        {
            dup2(this->infd[READ_END], STDIN_FILENO);
            dup2(this->outfd[WRITE_END], STDOUT_FILENO);
            dup2(this->errfd[WRITE_END], STDERR_FILENO);

            close(this->infd[WRITE_END]); // Child does not write to stdin
            close(this->outfd[READ_END]); // Child does not read from stdout
            close(this->errfd[READ_END]); // Child does not read from stderr

            execlp("bash", "bash", "-c", command.data(), nullptr);

            std::exit(EXIT_SUCCESS); // Exit CHILD
        }

        // PARENT
        if (pid < 0)
        {
            throw std::runtime_error("Failed to fork");
        }

        i32 stat = 0;
        waitpid(pid, &stat, 0);

        std::array<char, 256> buffer{};

        isize bytes_out = 0;
        do
        {
            bytes_out = read(this->outfd[READ_END], buffer.data(), buffer.size());
            this->out.append(buffer.data(), bytes_out);
        } while (bytes_out > 0);

        isize bytes_err = 0;
        do
        {
            bytes_err = read(this->errfd[READ_END], buffer.data(), buffer.size());
            this->err.append(buffer.data(), bytes_err);
        } while (bytes_err > 0);

        if (WIFEXITED(stat))
        {
            this->status = WEXITSTATUS(stat);
        }
    }

    ~Execute()
    {
        if (this->infd[READ_END] != 0)
        {
            close(this->infd[READ_END]);
        }
        if (this->infd[WRITE_END] != 0)
        {
            close(this->infd[WRITE_END]);
        }

        if (this->outfd[READ_END] != 0)
        {
            close(this->outfd[READ_END]);
        }
        if (this->outfd[WRITE_END] != 0)
        {
            close(this->outfd[WRITE_END]);
        }

        if (this->errfd[READ_END] != 0)
        {
            close(this->errfd[READ_END]);
        }
        if (this->errfd[WRITE_END] != 0)
        {
            close(this->errfd[WRITE_END]);
        }
    }

    [[nodiscard]] int
    exit_status() const noexcept
    {
        return this->status;
    }

    [[nodiscard]] const std::string
    standard_input() const noexcept
    {
        return this->in;
    }

    [[nodiscard]] const std::string
    standard_output() const noexcept
    {
        return this->out;
    }

    [[nodiscard]] const std::string
    standard_error() const noexcept
    {
        return this->err;
    }

  private:
    int status{0};

    std::string in{};  // standard input
    std::string out{}; // standard output
    std::string err{}; // standard error

    std::array<i32, 2> infd{0, 0};
    std::array<i32, 2> outfd{0, 0};
    std::array<i32, 2> errfd{0, 0};

    const i32 READ_END = 0;
    const i32 WRITE_END = 1;
};
} // namespace ztd::shell
