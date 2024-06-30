#!/bin/bash

# URL to use for the requests
URL="http://httpbin.org"

# Perform a GET request
echo "Performing a GET request to $URL/get"
curl -v "$URL/get"

# Perform a POST request
echo -e "\n\nPerforming a POST request to $URL/post with some data"
curl -v -X POST -d "name=ChatGPT&age=1" "$URL/post"

# Display HTTP headers
echo -e "\n\nDisplaying HTTP headers for GET request to $URL/get"
curl -I "$URL/get"

