# 🔄 Dynamic Thread Pool in C++  
> A lightweight, scalable thread-pool implementation with automatic worker resizing based on workload.

---

## ✅ Overview

This project implements a **dynamic thread pool** in C++ that automatically manages worker threads based on the number of pending tasks.

It:
- Maintains a queue of tasks
- Executes them via worker threads
- Scales **up** when the queue grows
- Scales **down** when work is completed

This approach reduces overhead and efficiently utilizes CPU resources.

---

## 🎯 Features

- ✅ Submit tasks asynchronously  
- ✅ Automatic scaling (increase / decrease worker count)  
- ✅ Thread-safe queue  
- ✅ Min / max thread limits  
- ✅ Efficient use of system resources  
- ✅ Modular and easy to integrate  

---

## 📂 Project Structure
threadpool-dynamic/
│
├── include/
│   └── thread_pool.h
│
├── src/
│   └── thread_pool.cpp
│
├── examples/
│   └── main.cpp
│
├── CMakeLists.txt
└── README.md
---

## ⚙️ Build & Run

### ✅ Build with g++

```bash
g++ examples/main.cpp src/thread_pool.cpp -I include -pthread -o threadpool
./threadpool
