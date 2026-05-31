# Network-Programming — C++ Socket Playbook 🚀

Welcome! This repo has the seeds of a Dedicated Chat Application written in C++, but it's just getting started. I began this project to get hands-on with socket programming and to escape the grind of the GATE‑CS syllabus and textbooks — I didn't realise this could turn into something really cool! 😄

## What’s in the repo now

- `server.cpp` — basic server-side socket code (work in progress)
- `client.cpp` — basic client-side socket code (work in progress)

> Right now these files are my playground for learning sockets. Expect minimal, focused examples rather than a polished app.

## Why this project? 🎯
I wanted a practical way to learn networking beyond theory and textbooks. Building a chat application is a perfect playground for TCP/UDP concepts, concurrency, and low-level system programming — and it’s fun to build!

## Future plans ✨
I plan to evolve this into a full-fledged Dedicated Chat Application in C++ with features like:

- Multi-client support with a robust server (thread-per-client or event-driven)
- User authentication & simple nicknames
- Private messages and chat rooms
- Message history persistence (simple file or lightweight DB)
- Clean command-line client UI and optional GUI later
- TLS/SSL support for encrypted transport
- Tests, CI, and docs

If it grows big enough, I might split modules, add a build system, and make cross-platform binaries.

## Quick start (how I test builds locally) 🛠️
Compile server and client with g++:

```bash
# in the project root
g++ -std=c++17 server.cpp -o server
g++ -std=c++17 client.cpp -o client

# run server in background
./server &

# run client
./client
```

(Adjust flags and concurrency model as the code evolves.)

## Project status
This project just started — early experiments only. If you’re reading this, welcome aboard! Contributions, ideas, and experiments are very welcome. 🚀

## Motivation (real talk) 💬
I started this to escape the textbook loop of GATE‑CS and actually build things. It began as a learning exercise in sockets and quickly felt like it could become something useful and fun. Let's see where it goes!

---

