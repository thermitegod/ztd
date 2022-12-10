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
    static constexpr i32 READ_END = 0;
    static constexpr i32 WRITE_END = 1;

    std::array<i32, 2> infd{0, 0};
    std::array<i32, 2> outfd{0, 0};
    std::array<i32, 2> errfd{0, 0};

    auto cleanup = [&]()
    {
        if (infd[READ_END])
            close(infd[READ_END]);
        if (infd[WRITE_END])
            close(infd[WRITE_END]);

        if (outfd[READ_END])
            close(outfd[READ_END]);
        if (outfd[WRITE_END])
            close(outfd[WRITE_END]);

        if (errfd[READ_END])
            close(errfd[READ_END]);
        if (errfd[WRITE_END])
            close(errfd[WRITE_END]);
    };

    if (pipe(infd.data()) == -1)
    {
        cleanup();
        throw std::runtime_error(std::strerror(errno));
    }

    if (pipe(outfd.data()) == -1)
    {
        cleanup();
        throw std::runtime_error(std::strerror(errno));
    }

    if (pipe(errfd.data()) == -1)
    {
        cleanup();
        throw std::runtime_error(std::strerror(errno));
    }

    pid_t pid;

    pid = fork();
    if (pid > 0) // PARENT
    {
        close(infd[READ_END]);   // Parent does not read from stdin
        close(outfd[WRITE_END]); // Parent does not write to stdout
        close(errfd[WRITE_END]); // Parent does not write to stderr

        if (write(infd[WRITE_END], this->standard_input.data(), this->standard_input.size()) < 0)
        {
            throw std::runtime_error(std::strerror(errno));
        }
        close(infd[WRITE_END]); // Done writing
    }
    else if (pid == 0) // CHILD
    {
        dup2(infd[READ_END], STDIN_FILENO);
        dup2(outfd[WRITE_END], STDOUT_FILENO);
        dup2(errfd[WRITE_END], STDERR_FILENO);

        close(infd[WRITE_END]); // Child does not write to stdin
        close(outfd[READ_END]); // Child does not read from stdout
        close(errfd[READ_END]); // Child does not read from stderr

        execlp("bash", "bash", "-c", command.data(), nullptr);
        std::exit(EXIT_SUCCESS); // Exit CHILD
    }

    // PARENT
    if (pid < 0)
    {
        cleanup();
        throw std::runtime_error("Failed to fork");
    }

    i32 status = 0;
    isize bytes;
    std::array<char, 256> buffer;

    waitpid(pid, &status, 0);

    bytes = 0;
    do
    {
        bytes = read(outfd[READ_END], buffer.data(), buffer.size());
        this->standard_output.append(buffer.data(), bytes);
    } while (bytes > 0);

    bytes = 0;
    do
    {
        bytes = read(errfd[READ_END], buffer.data(), buffer.size());
        this->standard_error.append(buffer.data(), bytes);
    } while (bytes > 0);

    if (WIFEXITED(status))
        exit_status = WEXITSTATUS(status);

    cleanup();
}
