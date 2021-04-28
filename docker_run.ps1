$path = Get-Location | Foreach-Object { $_.Path }
echo $path\src

docker run `
    --name repo_gem5 `
    -it `
    --volume $path\src:/usr/local/src `
    kyens0612/gem5_profile:latest