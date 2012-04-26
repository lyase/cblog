#!/bin/sh
valgrind --leak-check=yes --log-file=valgrind.out.txt ./exampleApp --docroot="static-content;/resources" --deploy-path="/" --no-compression --http-address=0.0.0.0 --http-port=8000 -c wt-config.xml
