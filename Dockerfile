FROM golang:1.14

# we don't have to do this because to go mods, but it is easy
WORKDIR $GOPATH/src/github.com/null-channel/studio-light-project

# copy all project files into container
COPY . .

# build and install the project
RUN go install -v ./...

# can really be any port
EXPOSE 8080

# run the project on contaienr start
CMD ["studio-lights"]
