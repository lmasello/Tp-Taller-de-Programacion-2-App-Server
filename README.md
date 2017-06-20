# tp-taller-de-programacion-2
Repository of the semestral project for the subject 'Taller de Programación II' of the University of Buenos Aires which consist of doing an application similar to Spotify.

## Build

### Build executable

```bash
cd Tp-Taller-de-Programacion-2-App-Server
cmake .
make
```

### Build .deb package
```bash
cd Tp-Taller-de-Programacion-2-App-Server
cmake .
make package
```

### Build docker image
```bash
docker build . --tag music-io-app-server
```

## run

### Executable:

```bash
./music-io-app-server
```

### Docker:

```bash
docker run music-io-app-server:latest
```

## Tests

### Run tests
To run tests execute:
```bash
make test
```

### Coverage
To run gcov + lcov execute:
```bash
make coverage
```
All files generated should be placed under the folder `coverage`. Just open with a browser `/coverage/index.html`
