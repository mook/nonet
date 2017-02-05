# nonet

This binary spawns a new network namespace (on Linux) so that the application it
launches has no network access.

## Installation

The binary must be installed suid root.

## Usage

`nonet <command> [args...]`

The command is searched in the path, and any arguments are passed unmodified.

## Warning

I have not written many suid binaries; while I believe there are no security
problems, it would be a good idea to review the code first.
