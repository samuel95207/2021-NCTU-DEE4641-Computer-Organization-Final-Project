# 2021-NCTU-DEE4641-Computer-Organization-Final-Project
* Requirement: Docker
* Run the following Commands to run docker
```
.\docker_run.ps1
```
* Run the following Commands to enter docker
```
docker exec -ti repo_gem5 bash
# or
./docker_join.ps1
```
* Run the following Commands in docker to build gem5
```
cd gem5_profile
scons build/X86/gem5.opt -j 9
```
* Run the following Commands in docker to run simulation
```
# String Matching
build/X86/gem5.opt configs/example/se.py -c String_Matching/main \
    --cpu-type=DerivO3CPU \
    --l1d_size=64B \
    --l1d_assoc=1 \
    --l1i_size=16kB \
    --caches \
    --mem-type=DDR4_2400_4x16 \
    --mem-channels=1 \
    --mem-size=4GB

# FM_index
build/X86/gem5.opt configs/example/se.py -c FM_index/main \
    --cpu-type=DerivO3CPU \
    --l1d_size=64B \
    --l1d_assoc=1 \
    --l1i_size=16kB \
    --caches \
    --mem-type=DDR4_2400_8x8 \
    --mem-channels=1 \
    --mem-size=4GB
```