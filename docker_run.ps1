$path = Get-Location | Foreach-Object { $_.Path }
echo $path\src

docker run `
    --name repo_gem5 `
    -it `
    --volume $path\src\String_Matching:/usr/local/src/gem5_profile/String_Matching `
    --volume $path\src\FM_index:/usr/local/src/gem5_profile/FM_index `
    kyens0612/gem5_profile:latest