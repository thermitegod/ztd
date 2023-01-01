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

#include <filesystem>

#include "../../types.hxx"

namespace ztd::proc
{
    class stat
    {
      public:
        stat();
        stat(pid_t pid);
        stat(const std::filesystem::path& path);

        /**
         *
         * proc/<PID>/stat entries
         *
         */

        /**
         * @brief The process ID.
         */
        [[nodiscard]] i32 pid() const noexcept;

        /**
         * @brief The filename of the executable.
         */
        [[nodiscard]] const std::string name() const noexcept;

        /**
         * @brief A char indicating the process state
         */
        [[nodiscard]] const std::string state() const noexcept;

        /**
         * @brief The PID of the parent of this process.
         */
        [[nodiscard]] i32 ppid() const noexcept;

        /**
         * @brief The process group ID of the process.
         */
        [[nodiscard]] i32 pgrp() const noexcept;

        /**
         * @brief The session ID of the process.
         */
        [[nodiscard]] i32 session() const noexcept;

        /**
         * @brief The ID of the foreground process group of the controlling terminal of the process.
         */
        [[nodiscard]] i32 tpgid() const noexcept;

        /**
         * @brief The number of minor faults the process has made which have not required loading a memory page from
         * disk.
         */
        [[nodiscard]] u64 minflt() const noexcept;

        /**
         * @brief The number of minor faults that the process's waited-for children have made.
         */
        [[nodiscard]] u64 cminflt() const noexcept;

        /**
         * @brief The  number  of  major faults the process has made which have required loading a memory page from
         * disk.
         */
        [[nodiscard]] u64 majflt() const noexcept;

        /**
         * @brief The number of major faults that the process's waited-for children have made.
         */
        [[nodiscard]] u64 cmajflt() const noexcept;

        /**
         * @brief Amount of time that this process has been scheduled in user mode, measured in clock ticks.
         */
        [[nodiscard]] u64 utime() const noexcept;

        /**
         * @brief Amount of time that this process has been scheduled in kernel mode, measured in clock ticks.
         */
        [[nodiscard]] u64 stime() const noexcept;

        /**
         * @brief Amount of time that this process's waited-for children have been scheduled in user mode, measured in
         * clock ticks.
         */
        [[nodiscard]] i64 cutime() const noexcept;

        /**
         * @brief Amount of time that this process's waited-for children have been scheduled in kernel mode, measured in
         * clock ticks.
         */
        [[nodiscard]] i64 cstime() const noexcept;

        /**
         * @brief For processes running under a non-real-time scheduling policy, this is the raw nice value as
         * represented in the kernel.
         */
        [[nodiscard]] i64 priority() const noexcept;

        /**
         * @brief The nice value (see setpriority(2)), a value in the range 19 (low priority) to -20 (high priority).
         */
        [[nodiscard]] i64 nice() const noexcept;

        /**
         * @brief Number of threads in this process.
         */
        [[nodiscard]] i64 num_threads() const noexcept;

        /**
         * @brief The time the process started after system boot.
         */
        [[nodiscard]] u64 starttime() const noexcept;

        /**
         * @brief Virtual memory size in bytes.
         */
        [[nodiscard]] u64 vsize() const noexcept;

        /**
         * @brief Resident Set Size: number of pages the process has in real memory.
         */
        [[nodiscard]] i64 rss() const noexcept;

        /**
         * @brief Signal to be sent to parent when we die.
         */
        [[nodiscard]] i32 exit_signal() const noexcept;

        /**
         * @brief CPU number last executed on.
         */
        [[nodiscard]] i32 processor() const noexcept;

        /**
         * @brief The thread's exit status in the form reported by waitpid(2).
         */
        [[nodiscard]] i32 exit_code() const noexcept;

        // check current state
        [[nodiscard]] bool is_running() const noexcept;
        [[nodiscard]] bool is_sleeping() const noexcept;
        [[nodiscard]] bool is_waiting() const noexcept;
        [[nodiscard]] bool is_zombie() const noexcept;
        [[nodiscard]] bool is_stopped() const noexcept;
        [[nodiscard]] bool is_trace_sropped() const noexcept;
        [[nodiscard]] bool is_dead() const noexcept;
        [[nodiscard]] bool is_idle() const noexcept;

        // Convenience functions

        /**
         * @brief Current execution time (utime + stime) / SC_CLK_TCK
         */
        [[nodiscard]] f64 etime() const noexcept;

      private:
        void populate(const std::filesystem::path& path);

        i32 m_pid{};
        std::string m_name{};
        std::string m_state{};
        i32 m_ppid{};
        i32 m_pgrp{};
        i32 m_session{};
        // i32 m_tty_nr{};
        i32 m_tpgid{};
        // u32 m_flags{};
        u64 m_minflt{};
        u64 m_cminflt{};
        u64 m_majflt{};
        u64 m_cmajflt{};
        u64 m_utime{};
        u64 m_stime{};
        i64 m_cutime{};
        i64 m_cstime{};
        i64 m_priority{};
        i64 m_nice{};
        i64 m_num_threads{};
        // i64 m_itrealvalue{};
        u64 m_starttime{};
        u64 m_vsize{};
        i64 m_rss{};
        // u64 m_rsslim{};
        // u64 m_startcode{};
        // u64 m_endcode{};
        // u64 m_startstack{};
        // u64 m_kstkesp{};
        // u64 m_kstkeip{};
        // u64 m_signal{};
        // u64 m_blocked{};
        // u64 m_sigignore{};
        // u64 m_sigcatch{};
        // u64 m_wchan{};
        // u64 m_nswap{};
        // u64 m_cnswap{};
        i32 m_exit_signal{};
        i32 m_processor{};
        // u32 m_rt_priority{};
        // u32 m_policy{};
        // u64 m_delayacct_blkio_ticks{};
        // u64 m_guest_time{};
        // i64 m_cguest_time{};
        // u64 m_start_data{};
        // u64 m_end_data{};
        // u64 m_start_brk{};
        // u64 m_arg_start{};
        // u64 m_arg_end{};
        // u64 m_env_start{};
        // u64 m_env_end{};
        i32 m_exit_code{};
    };
} // namespace ztd::proc
