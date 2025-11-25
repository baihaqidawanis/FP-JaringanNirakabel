
# 👨‍💻 Team Members — Final Project Wireless Network
- Muhammad Baihaqi Dawanis - 5025231177
- Abimanyu Dananedra Andarfebano - 5025231182

# 🔐 AODV-Trust Protocol  
Secure Routing for Mobile Ad-hoc Networks (MANET)

Modifikasi protokol **AODV** pada simulator **NS-3** dengan mekanisme **Trust Management** untuk meningkatkan keamanan terhadap *blackhole attack* dan perilaku node berbahaya.  

Repositori ini menunjukkan pendekatan routing aman menggunakan reputasi dinamis, filtering node jahat, serta mode perbandingan antara protokol **AODV standar** dan versi **AODV-Trust**.

---

## 🚀 Key Features

### 🔒 Security Mechanism
- **Trust Table System**
  - Setiap node memiliki nilai reputasi **0.0–1.0** berdasarkan perilaku forwarding paket.
- **Malicious Node Filtering**
  - Node dengan nilai trust < **0.4** otomatis di-*block*.
- **Reward & Penalty Logic**
  - Trust naik saat forwarding sukses  
  - Trust turun signifikan saat loss terdeteksi

---

### 🏛 System Architecture
| Feature | Status |
|--------|--------|
| Dual Operation Mode | ✔ Secure (AODV-Trust) & Standard AODV |
| Real-time Logging | ✔ Trust updates, PDR, alerts |
| Modular Helper Class | ✔ Install to any node set |

---

### 📊 Visualization & Analysis
- **NetAnim XML Integration**
- **Flow Monitor**: menghitung TX/RX packets, throughput, dan Packet Delivery Ratio (PDR)

---

## 📂 Project Structure (Files of Interest)

| File | Deskripsi |
|------|-----------|
| `src/aodv-trust/model/aodv-trust-routing-protocol.cc` | Implementasi inti trust & filtering |
| `src/aodv-trust/model/aodv-trust-routing-protocol.h` | Struktur Trust Table & parameter |
| `src/aodv-trust/helper/aodv-trust-helper.cc` | Instalasi protokol pada node |
| `scratch/aodv-trust-sim.cc` | Skrip simulasi utama |

---

## 🛠️ Requirements

| Komponen | Versi |
|----------|--------|
| OS | Ubuntu 20.04 / 22.04 / WSL2 |
| Compiler | GCC / G++ sesuai NS-3 |
| NS-3 Version | **3.41** |
| Build System | Waf / CMake |

---

## 📦 Installation & Setup

### 1️⃣ Install Dependencies

```
sudo apt update
sudo apt install build-essential python3-dev cmake git qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools -y
```
### 2️⃣ Clone Repository
```git clone <LINK_REPOSITORY_GITHUB_ANDA>
cd ns3-aodv-trust
```

### 🏗 Build Instructions
Bersihkan Build lama
```
./ns3 clean
```
Configure 
```
./ns3 configure --enable-examples --disable-tests
```
compile 
```
./ns3 build
```

## ▶️ How to Run Simulations
### 1. Secure Mode (AODV-Trust)
```
./ns3 run "scratch/aodv-trust-sim --useTrust=true"
```
Expected Output:
```
===============================================
>>> RUNNING MODE: AODV-TRUST (SECURE)       <<<
>>> Mekanisme filtering node jahat: AKTIF   <<<
===============================================
```
### 2. Standard Mode (Baseline AODV)
```
./ns3 run "scratch/aodv-trust-sim --useTrust=false"
```
Expected output
```
===============================================
>>> RUNNING MODE: AODV STANDARD (INSECURE)  <<<
>>> Mekanisme filtering node jahat: MATI    <<<
===============================================
```

### 📽 NetAnim Visualization
XML trace file otomatis dibuat setelah simulasi:
| Mode | file |
|----------|--------|
| Secure| anim-trust.xml|
| Standard| anim-std.xml |

---
### Cara buka di NetAnim:
- Buka aplikasi NetAnim
- Klik Open
- Pilih file XML
- Tekan Play

### Legend
Legend:

🟢 Source Node

🔴 Destination Node

🔵 Paket/Link Transmission




# The Network Simulator, Version 3

[![codecov](https://codecov.io/gh/nsnam/ns-3-dev-git/branch/master/graph/badge.svg)](https://codecov.io/gh/nsnam/ns-3-dev-git/branch/master/)
[![Gitlab CI](https://gitlab.com/nsnam/ns-3-dev/badges/master/pipeline.svg)](https://gitlab.com/nsnam/ns-3-dev/-/pipelines)
[![Github CI](https://github.com/nsnam/ns-3-dev-git/actions/workflows/per_commit.yml/badge.svg)](https://github.com/nsnam/ns-3-dev-git/actions)

[![Latest Release](https://gitlab.com/nsnam/ns-3-dev/-/badges/release.svg)](https://gitlab.com/nsnam/ns-3-dev/-/releases)

## Table of Contents

* [Overview](#overview-an-open-source-project)
* [Building ns-3](#building-ns-3)
* [Testing ns-3](#testing-ns-3)
* [Running ns-3](#running-ns-3)
* [ns-3 Documentation](#ns-3-documentation)
* [Working with the Development Version of ns-3](#working-with-the-development-version-of-ns-3)
* [Contributing to ns-3](#contributing-to-ns-3)
* [Reporting Issues](#reporting-issues)
* [ns-3 App Store](#ns-3-app-store)

> **NOTE**: Much more substantial information about ns-3 can be found at
<https://www.nsnam.org>

## Overview: An Open Source Project

ns-3 is a free open source project aiming to build a discrete-event
network simulator targeted for simulation research and education.
This is a collaborative project; we hope that
the missing pieces of the models we have not yet implemented
will be contributed by the community in an open collaboration
process. If you would like to contribute to ns-3, please check
the [Contributing to ns-3](#contributing-to-ns-3) section below.

This README excerpts some details from a more extensive
tutorial that is maintained at:
<https://www.nsnam.org/documentation/latest/>

## Building ns-3

The code for the framework and the default models provided
by ns-3 is built as a set of libraries. User simulations
are expected to be written as simple programs that make
use of these ns-3 libraries.

To build the set of default libraries and the example
programs included in this package, you need to use the
`ns3` tool. This tool provides a Waf-like API to the
underlying CMake build manager.
Detailed information on how to use `ns3` is included in the
[quick start guide](doc/installation/source/quick-start.rst).

Before building ns-3, you must configure it.
This step allows the configuration of the build options,
such as whether to enable the examples, tests and more.

To configure ns-3 with examples and tests enabled,
run the following command on the ns-3 main directory:

```shell
./ns3 configure --enable-examples --enable-tests
```

Then, build ns-3 by running the following command:

```shell
./ns3 build
```

By default, the build artifacts will be stored in the `build/` directory.

### Supported Platforms

The current codebase is expected to build and run on the
set of platforms listed in the [release notes](RELEASE_NOTES.md)
file.

Other platforms may or may not work: we welcome patches to
improve the portability of the code to these other platforms.

## Testing ns-3

ns-3 contains test suites to validate the models and detect regressions.
To run the test suite, run the following command on the ns-3 main directory:

```shell
./test.py
```

More information about ns-3 tests is available in the
[test framework](doc/manual/source/test-framework.rst) section of the manual.

## Running ns-3

On recent Linux systems, once you have built ns-3 (with examples
enabled), it should be easy to run the sample programs with the
following command, such as:

```shell
./ns3 run simple-global-routing
```

That program should generate a `simple-global-routing.tr` text
trace file and a set of `simple-global-routing-xx-xx.pcap` binary
PCAP trace files, which can be read by `tcpdump -n -tt -r filename.pcap`.
The program source can be found in the `examples/routing` directory.

## Running ns-3 from Python

If you do not plan to modify ns-3 upstream modules, you can get
a pre-built version of the ns-3 python bindings.

```shell
pip install --user ns3
```

If you do not have `pip`, check their documents
on [how to install it](https://pip.pypa.io/en/stable/installation/).

After installing the `ns3` package, you can then create your simulation python script.
Below is a trivial demo script to get you started.

```python
from ns import ns

ns.LogComponentEnable("Simulator", ns.LOG_LEVEL_ALL)

ns.Simulator.Stop(ns.Seconds(10))
ns.Simulator.Run()
ns.Simulator.Destroy()
```

The simulation will take a while to start, while the bindings are loaded.
The script above will print the logging messages for the called commands.

Use `help(ns)` to check the prototypes for all functions defined in the
ns3 namespace. To get more useful results, query specific classes of
interest and their functions e.g., `help(ns.Simulator)`.

Smart pointers `Ptr<>` can be differentiated from objects by checking if
`__deref__` is listed in `dir(variable)`. To dereference the pointer,
use `variable.__deref__()`.

Most ns-3 simulations are written in C++ and the documentation is
oriented towards C++ users. The ns-3 tutorial programs (`first.cc`,
`second.cc`, etc.) have Python equivalents, if you are looking for
some initial guidance on how to use the Python API. The Python
API may not be as full-featured as the C++ API, and an API guide
for what C++ APIs are supported or not from Python do not currently exist.
The project is looking for additional Python maintainers to improve
the support for future Python users.

## ns-3 Documentation

Once you have verified that your build of ns-3 works by running
the `simple-global-routing` example as outlined in the [running ns-3](#running-ns-3)
section, it is quite likely that you will want to get started on reading
some ns-3 documentation.

All of that documentation should always be available from
the ns-3 website: <https://www.nsnam.org/documentation/>.

This documentation includes:

* a tutorial
* a reference manual
* models in the ns-3 model library
* a wiki for user-contributed tips: <https://www.nsnam.org/wiki/>
* API documentation generated using doxygen: this is
  a reference manual, most likely not very well suited
  as introductory text:
  <https://www.nsnam.org/doxygen/index.html>

## Working with the Development Version of ns-3

If you want to download and use the development version of ns-3, you
need to use the tool `git`. A quick and dirty cheat sheet is included
in the manual, but reading through the Git
tutorials found in the Internet is usually a good idea if you are not
familiar with it.

If you have successfully installed Git, you can get
a copy of the development version with the following command:

```shell
git clone https://gitlab.com/nsnam/ns-3-dev.git
```

However, we recommend to follow the GitLab guidelines for starters,
that includes creating a GitLab account, forking the ns-3-dev project
under the new account's name, and then cloning the forked repository.
You can find more information in the [manual](https://www.nsnam.org/docs/manual/html/working-with-git.html).

## Contributing to ns-3

The process of contributing to the ns-3 project varies with
the people involved, the amount of time they can invest
and the type of model they want to work on, but the current
process that the project tries to follow is described in the
[contributing code](https://www.nsnam.org/developers/contributing-code/)
website and in the [CONTRIBUTING.md](CONTRIBUTING.md) file.

## Reporting Issues

If you would like to report an issue, you can open a new issue in the
[GitLab issue tracker](https://gitlab.com/nsnam/ns-3-dev/-/issues).
Before creating a new issue, please check if the problem that you are facing
was already reported and contribute to the discussion, if necessary.

## ns-3 App Store

The official [ns-3 App Store](https://apps.nsnam.org/) is a centralized directory
listing third-party modules for ns-3 available on the Internet.

More information on how to submit an ns-3 module to the ns-3 App Store is available
in the [ns-3 App Store documentation](https://www.nsnam.org/docs/contributing/html/external.html).
