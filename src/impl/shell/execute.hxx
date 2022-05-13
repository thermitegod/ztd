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

#ifndef ZTD_SHELL_HEADER
#error "Only <ztd-shell.hxx> can be included directly"
#endif

#pragma once

#include <string>

#include <array>

#include <cstring>
#include <stdexcept>

#include <sys/types.h>
#include <sys/wait.h>

namespace ztd
{
    class Execute
    {
      public:
        int exit_status = 0;

        std::string standard_input;
        std::string standard_output;
        std::string standard_error;

        // Execute(){};

        Execute(const std::string& command)
        {
            const int READ_END = 0;
            const int WRITE_END = 1;

            int infd[2] = {0, 0};
            int outfd[2] = {0, 0};
            int errfd[2] = {0, 0};

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

            int rc;

            rc = pipe(infd);
            if (rc == -1)
            {
                cleanup();
                throw std::runtime_error(std::strerror(errno));
            }

            rc = pipe(outfd);
            if (rc == -1)
            {
                cleanup();
                throw std::runtime_error(std::strerror(errno));
            }

            rc = pipe(errfd);
            if (rc == -1)
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

                if (write(infd[WRITE_END], standard_input.data(), standard_input.size()) < 0)
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

                execlp("bash", "bash", "-c", command.c_str(), nullptr);
                std::exit(EXIT_SUCCESS); // Exit CHILD
            }

            // PARENT
            if (pid < 0)
            {
                cleanup();
                throw std::runtime_error("Failed to fork");
            }

            int status = 0;
            ssize_t bytes;
            std::array<char, 256> buffer;

            waitpid(pid, &status, 0);

            bytes = 0;
            do {
                bytes = read(outfd[READ_END], buffer.data(), buffer.size());
                standard_output.append(buffer.data(), bytes);
            } while (bytes > 0);

            bytes = 0;
            do {
                bytes = read(errfd[READ_END], buffer.data(), buffer.size());
                standard_error.append(buffer.data(), bytes);
            } while (bytes > 0);

            if (WIFEXITED(status))
                exit_status = WEXITSTATUS(status);

            cleanup();
        }
    };
} // namespace ztd
