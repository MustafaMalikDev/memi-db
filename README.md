# memi-db
An experimental in-memory database inspired by and based on Redis.

This is for pure learning purposes to better understand how in-memory databases work and get familiar with high performance codebases such as Redis. In no way is this database appropriate for production, but it is a starting point.

No **AI** related tools will be used for this project. Pure learning.

## Quick Overview

a lightweight, experimental in-memory key-value data store to explore handling structures and types cached in memory for fast access.

It supports out of the box:
- Get, Put, Update, Delete operations
- Primitive types
- TTLs (Time to Live) for objects

## Tech Stack

- C++11
- make
- [ligen2](https://github.com/MustafaMalikDev/ligen.git)

A simple tech stack because I want to avoid using libraries and get more hands-on experience.

## Installation

Due to this project being experimental and for learning, I am not responsible if you choose to build and run this project and I am not liable for any potential damage or problems that may occur.

```
# Clone the repository
$ git clone https://github.com/your-username/memi-db.git
$ cd memi-db

# Build the project
$ make all
```

## Running memi-db

```
# Run the project
$ cd build

# Specify --port <PORT> to change the default port (6721)
$ ./memidb
```

## Basic Usage

```
# Server
# Running on port 6721
$ ./memdb

# Client
# Specify --port <PORT> to change the default port (6721)
# ./memdb-cli

$ 127.0.0.1:6721 > SET KEY foo VALUE 100
$ > OK
$ 127.0.0.1:6721 > GET KEY foo
$ > 100
```

memi-db relies on the msql (memi-db simple query language) syntax to execute statements. Documentation will be provided in good time for better understanding.

You can utilise msql to write custom drivers in other languages without having to rely on a pure C++ API.

## Planned Features

| Command | Status | Description |
| --- | --- | --- |
| `PING` | ✅ Planned | Health check |
| `GET` / `SET` | ✅ Planned | Basic key-value operations |
| `DELETE` / `UPDATE` | ✅ Planned | Key management |


## Tests and Automated Workflows

Coming Soon.

## Contributing

If you want to fix a bug or request a feature please follow the following constraints:

- a new branch as format `<feat-name>`
- semantic commit messages
- clang-formatted code and tested
- compatible for macOS 15+ (aarch64 only)
- submitted a pull request with a detailed description

## License

Distributed under GPLv3. See LICENSE for more information.