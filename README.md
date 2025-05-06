Building instructions:

```bash
git clone https://github.com/kholdfuzion/Goldenrecomp --recurse-submodules
```

* Build a TLBFREE ROM from this branch of the decompilation project:
https://github.com/kholdfuzion/goldeneye_src/compare/TBLFREE_NOCOMPRESSION

* place ge007.tlbfree.elf and ge007.tlbfree.z64 on the root of the repo.

* compile N64Recomp from this fork:
https://github.com/kholdfuzion/N64Recomp/commits/main/
or just use the included binaries in this repo (Windows only atm)

```bash
.\N64Recomp.exe us.toml
.\N64Recomp.exe us.toml --dump-context
.\RSPRecomp.exe aspMain.us.toml
```

* Open the project folder with visual studio
* Select the GoldenRecomp.exe target
* Set either x64-Debug or z64-ReleaseWithDebInfo as required
* Build
