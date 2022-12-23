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
#include <string_view>

#include <filesystem>

#include <fstream>
#include <sstream>

#include <unistd.h>

#include <sys/types.h>

#include <fmt/format.h>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_utils.hxx"
#include "ztd/internal/string_python.hxx"

#include "ztd/internal/linux/proc/stat.hxx"

constexpr u8 idx_pid = 0;
constexpr u8 idx_name = 1;
constexpr u8 idx_state = 2;
constexpr u8 idx_ppid = 3;
constexpr u8 idx_pgrp = 4;
constexpr u8 idx_session = 5;
// constexpr u8 idx_tty_nr = 6;
constexpr u8 idx_tpgid = 7;
// constexpr u8 idx_flags = 8;
constexpr u8 idx_minflt = 9;
constexpr u8 idx_cminflt = 10;
constexpr u8 idx_majflt = 11;
constexpr u8 idx_cmajflt = 12;
constexpr u8 idx_utime = 13;
constexpr u8 idx_stime = 14;
constexpr u8 idx_cutime = 15;
constexpr u8 idx_cstime = 16;
constexpr u8 idx_priority = 17;
constexpr u8 idx_nice = 18;
constexpr u8 idx_num_threads = 19;
// constexpr u8 idx_itrealvalue = 20;
constexpr u8 idx_starttime = 21;
constexpr u8 idx_vsize = 22;
constexpr u8 idx_rss = 23;
// constexpr u8 idx_rsslim = 24;
// constexpr u8 idx_startcode = 25;
// constexpr u8 idx_endcode = 26;
// constexpr u8 idx_startstack = 27;
// constexpr u8 idx_kstkesp = 28;
// constexpr u8 idx_kstkeip = 29;
// constexpr u8 idx_signal = 30;
// constexpr u8 idx_blocked = 31;
// constexpr u8 idx_sigignore = 32;
// constexpr u8 idx_sigcatch = 33;
// constexpr u8 idx_wchan = 34;
// constexpr u8 idx_nswap = 35;
// constexpr u8 idx_cnswap = 36;
constexpr u8 idx_exit_signal = 37;
constexpr u8 idx_processor = 38;
// constexpr u8 idx_rt_priority = 39;
// constexpr u8 idx_policy = 40;
// constexpr u8 idx_delayacct_blkio_ticks = 41;
// constexpr u8 idx_guest_time = 42;
// constexpr u8 idx_cguest_time = 43;
// constexpr u8 idx_start_data = 44;
// constexpr u8 idx_end_data = 45;
// constexpr u8 idx_start_brk = 46;
// constexpr u8 idx_arg_start = 47;
// constexpr u8 idx_arg_end = 48;
// constexpr u8 idx_env_start = 49;
// constexpr u8 idx_env_end = 50;
constexpr u8 idx_exit_code = 51;

ztd::proc::stat::stat()
{
    this->populate("/proc/self/stat");
}

ztd::proc::stat::stat(pid_t pid)
{
    const std::filesystem::path path = fmt::format("/proc/{}/stat", pid);

    this->populate(path);
}

ztd::proc::stat::stat(const std::filesystem::path& path)
{
    this->populate(path);
}

void
ztd::proc::stat::populate(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (file.is_open())
    {
        std::stringstream stream;
        stream << file.rdbuf();

        const std::string raw_stat = stream.str();

        const auto stat_data = ztd::split(raw_stat, " ");

        this->m_pid = std::stoi(stat_data.at(idx_pid));
        this->m_name = stat_data.at(idx_name);
        this->m_state = stat_data.at(idx_state);
        this->m_ppid = std::stoi(stat_data.at(idx_ppid));
        this->m_pgrp = std::stoi(stat_data.at(idx_pgrp));
        this->m_session = std::stoi(stat_data.at(idx_session));
        this->m_tpgid = std::stoi(stat_data.at(idx_tpgid));
        this->m_minflt = std::stoul(stat_data.at(idx_minflt));
        this->m_cminflt = std::stoul(stat_data.at(idx_cminflt));
        this->m_majflt = std::stoul(stat_data.at(idx_majflt));
        this->m_cmajflt = std::stoul(stat_data.at(idx_cmajflt));
        this->m_utime = std::stoul(stat_data.at(idx_utime));
        this->m_stime = std::stoul(stat_data.at(idx_stime));
        this->m_cutime = std::stol(stat_data.at(idx_cutime));
        this->m_cstime = std::stol(stat_data.at(idx_cstime));
        this->m_priority = std::stol(stat_data.at(idx_priority));
        this->m_nice = std::stol(stat_data.at(idx_nice));
        this->m_num_threads = std::stol(stat_data.at(idx_num_threads));
        this->m_starttime = std::stoul(stat_data.at(idx_starttime));
        this->m_vsize = std::stoul(stat_data.at(idx_vsize));
        this->m_rss = std::stol(stat_data.at(idx_rss));
        this->m_exit_signal = std::stol(stat_data.at(idx_exit_signal));
        this->m_processor = std::stol(stat_data.at(idx_processor));
        this->m_exit_code = std::stol(stat_data.at(idx_exit_code));
    }

    // special post processing

    // name
    if (this->m_name.size() == 16)
    { // possible truncated value
        const auto exe_path = path.parent_path() / "exe";
        this->m_name = std::filesystem::read_symlink(exe_path).filename();
    }
    else
    {
        this->m_name = ztd::strip(this->m_name, "()");
    }
}

/**
 * proc/<PID>/stat entries
 */

i32
ztd::proc::stat::pid() const noexcept
{
    return this->m_pid;
}

const std::string
ztd::proc::stat::name() const noexcept
{
    return this->m_name;
}

const std::string
ztd::proc::stat::state() const noexcept
{
    return this->m_state;
}

i32
ztd::proc::stat::ppid() const noexcept
{
    return this->m_ppid;
}

i32
ztd::proc::stat::pgrp() const noexcept
{
    return this->m_pgrp;
}

i32
ztd::proc::stat::session() const noexcept
{
    return this->m_session;
}

i32
ztd::proc::stat::tpgid() const noexcept
{
    return this->m_tpgid;
}

u64
ztd::proc::stat::minflt() const noexcept
{
    return this->m_minflt;
}

u64
ztd::proc::stat::cminflt() const noexcept
{
    return this->m_cminflt;
}

u64
ztd::proc::stat::majflt() const noexcept
{
    return this->m_majflt;
}

u64
ztd::proc::stat::cmajflt() const noexcept
{
    return this->m_cmajflt;
}

u64
ztd::proc::stat::utime() const noexcept
{
    return this->m_utime;
}

u64
ztd::proc::stat::stime() const noexcept
{
    return this->m_stime;
}

i64
ztd::proc::stat::cutime() const noexcept
{
    return this->m_cutime;
}

i64
ztd::proc::stat::cstime() const noexcept
{
    return this->m_cstime;
}

i64
ztd::proc::stat::priority() const noexcept
{
    return this->m_priority;
}

i64
ztd::proc::stat::nice() const noexcept
{
    return this->m_nice;
}

i64
ztd::proc::stat::num_threads() const noexcept
{
    return this->m_num_threads;
}

u64
ztd::proc::stat::starttime() const noexcept
{
    return this->m_starttime;
}

u64
ztd::proc::stat::vsize() const noexcept
{
    return this->m_vsize;
}

i64
ztd::proc::stat::rss() const noexcept
{
    return this->m_rss;
}

i32
ztd::proc::stat::exit_signal() const noexcept
{
    return this->m_exit_signal;
}

i32
ztd::proc::stat::processor() const noexcept
{
    return this->m_processor;
}

i32
ztd::proc::stat::exit_code() const noexcept
{
    return this->m_exit_code;
}

/**
 * State checking
 */

bool
ztd::proc::stat::is_running() const noexcept
{
    return ztd::same(this->m_state, "R");
}

bool
ztd::proc::stat::is_sleeping() const noexcept
{
    return ztd::same(this->m_state, "S");
}

bool
ztd::proc::stat::is_waiting() const noexcept
{
    return ztd::same(this->m_state, "D");
}

bool
ztd::proc::stat::is_zombie() const noexcept
{
    return ztd::same(this->m_state, "Z");
}

bool
ztd::proc::stat::is_stopped() const noexcept
{
    return ztd::same(this->m_state, "T");
}

bool
ztd::proc::stat::is_trace_sropped() const noexcept
{
    return ztd::same(this->m_state, "t");
}

bool
ztd::proc::stat::is_dead() const noexcept
{
    return ztd::same(this->m_state, "X");
}

bool
ztd::proc::stat::is_idle() const noexcept
{
    return ztd::same(this->m_state, "I");
}

/**
 * Convenience functions
 */

f64
ztd::proc::stat::etime() const noexcept
{
    const i64 clock_ticks = ::sysconf(_SC_CLK_TCK);
    const f64 execution_time = (this->utime() + this->stime()) / (f64)clock_ticks;
    return execution_time;
}
