#ifndef CGROUP_H
#define CGROUP_H

#define CGROUP_DEFAULT_ROOT "/sys/fs/cgroup"
#define CGROUP_NAME "cjail.%d"

int cgroup_set_root(const char *path) __nonnull((1));
int cgroup_create(const char* subsystem) __nonnull((1));
int cgroup_read(const char* subsystem, const char *name, const char *fmt, ...)
    __attribute__((format (scanf, 3, 4))) __nonnull((1, 2, 3));
int cgroup_write(const char* subsystem, const char *name, const char *fmt, ...)
    __attribute__((format (printf, 3, 4))) __nonnull((1, 2, 3));
int cgroup_open_tasks(const char* subsystem) __nonnull((1));
int cgroup_destory(const char* subsystem) __nonnull((1));

#endif
