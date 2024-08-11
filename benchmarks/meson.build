gbenchmark_dep = dependency('benchmark', required : true)
glibmm_dep = dependency('glibmm-2.68', required : true)

## Benchmark Suite files

sources = files(
    'src/main.cxx',
    'src/utils.cxx',

    # BASE
    'src/base/string-python.cxx',
)

benchmark_suite = build_target(
    'benchmark_suite',
    sources: sources,
    target_type: 'executable',
    include_directories: incdir,
    install : false,
    dependencies: [
        gbenchmark_dep,
        ztd_dep,
    ],
)

## Benchmark Suite Checksums

sources = files(
    'src/main.cxx',
    'src/utils.cxx',

    'src/base/checksum.cxx',
)

benchmark_suite = build_target(
    'benchmark_suite_checksum',
    sources: sources,
    target_type: 'executable',
    include_directories: incdir,
    install : false,
    dependencies: [
        gbenchmark_dep,
        glibmm_dep,
        ztd_dep,
    ],
)
