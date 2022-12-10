/**
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

#include <string>

#include <array>

#include <cstring>
#include <stdexcept>

#include <sys/types.h>
#include <sys/wait.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/shell/execute.hxx"

ztd::Execute::Execute(std::string_view command)
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
        close(this->infd[this->READ_END]);   // Parent does not read from stdin
        close(this->outfd[this->WRITE_END]); // Parent does not write to stdout
        close(this->errfd[this->WRITE_END]); // Parent does not write to stderr

        if (write(this->infd[this->WRITE_END], this->standard_input.data(), this->standard_input.size()) < 0)
        {
            throw std::runtime_error(std::strerror(errno));
        }
        close(this->infd[this->WRITE_END]); // Done writing
    }
    else if (pid == 0) // CHILD
    {
        dup2(this->infd[this->READ_END], STDIN_FILENO);
        dup2(this->outfd[this->WRITE_END], STDOUT_FILENO);
        dup2(this->errfd[this->WRITE_END], STDERR_FILENO);

        close(this->infd[this->WRITE_END]); // Child does not write to stdin
        close(this->outfd[this->READ_END]); // Child does not read from stdout
        close(this->errfd[this->READ_END]); // Child does not read from stderr

        execlp("bash", "bash", "-c", command.data(), nullptr);

        std::exit(EXIT_SUCCESS); // Exit CHILD
    }

    // PARENT
    if (pid < 0)
    {
        throw std::runtime_error("Failed to fork");
    }

    i32 status = 0;
    waitpid(pid, &status, 0);

    std::array<char, 256> buffer;

    isize bytes_out = 0;
    do
    {
        bytes_out = read(this->outfd[this->READ_END], buffer.data(), buffer.size());
        this->standard_output.append(buffer.data(), bytes_out);
    } while (bytes_out > 0);

    isize bytes_err = 0;
    do
    {
        bytes_err = read(this->errfd[this->READ_END], buffer.data(), buffer.size());
        this->standard_error.append(buffer.data(), bytes_err);
    } while (bytes_err > 0);

    if (WIFEXITED(status))
        this->exit_status = WEXITSTATUS(status);
}

ztd::Execute::~Execute()
{
    if (this->infd[this->READ_END])
        close(this->infd[this->READ_END]);
    if (this->infd[this->WRITE_END])
        close(this->infd[this->WRITE_END]);

    if (this->outfd[this->READ_END])
        close(this->outfd[this->READ_END]);
    if (this->outfd[this->WRITE_END])
        close(this->outfd[this->WRITE_END]);

    if (this->errfd[this->READ_END])
        close(this->errfd[this->READ_END]);
    if (this->errfd[this->WRITE_END])
        close(this->errfd[this->WRITE_END]);
}
