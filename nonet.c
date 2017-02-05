#define _GNU_SOURCE

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rv = unshare(CLONE_NEWNET);
    if (rv != 0) {
        fprintf(stderr, "Failed to unshare network: %s\n", strerror(errno));
        return 1;
    }

    uid_t ruid = getuid();

    errno = 0;
    struct passwd *user = getpwuid(ruid);
    if (!user) {
        fprintf(stderr, "Failed to get info for uid %d: %s\n", ruid, strerror(errno));
        return 1;
    }

    rv = initgroups(user->pw_name, user->pw_gid);
    if (rv != 0) {
        fprintf(stderr, "Failed to reset groups for %s: %s\n", user->pw_name, strerror(errno));
        return 1;
    }

    rv = seteuid(ruid);
    if (rv != 0) {
        fprintf(stderr, "Failed to set EUID for %s: %s\n", user->pw_name, strerror(errno));
        return 1;
    }

    rv = execvp(argv[1], argv + 1);
    if (rv != 0) {
        fprintf(stderr, "Failed to execute child: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
