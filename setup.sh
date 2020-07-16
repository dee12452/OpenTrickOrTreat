installLibs() {
    cd thirdparty
    for dir in */
    do
        echo "$dir"
        cd $dir
        mkdir -p ../../include/$dir
        cmake . && make
        cp -r src/*.h ../../include/$dir
        cp *.a ../../lib/
        cd ../../
    done
    cd ..
}

rm -rf include lib
mkdir include
mkdir lib
installLibs