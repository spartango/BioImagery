#!/bin/sh

# Utils

checksuccess() 
{
    if [[ $? == 0 ]]; then
        echo "[    OK    ]"
    else
        echo "[   FAIL   ]"
    fi
}

checkpermissions() 
{
    if [[ `whoami` != "root" ]]; then
        echo "[   FAIL   ] Insufficient permissions" 
        echo "[==========]"    
        exit 1    
    fi
}

# Deps

install_rapidjson() 
{
    #Rapid json
    echo "[    >>    ] RapidJSON"
    cp -r rapidjson-read-only/include/rapidjson /usr/include/
    checksuccess
}



echo [==========] Installing Dependencies
checkpermissions

install_rapidjson

echo [==========] Done Installing

