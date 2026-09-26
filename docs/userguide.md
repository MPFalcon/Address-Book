# Address Book

The application is designed to hold contact information within a small organization or home use

## Dependencies

- GTK 4 is recuired to build and run the application

    - `sudo apt install libgtk-4-dev pkg-config cmake`

## How to build

- Run the following to build the release build version

    - `cmake --workflow --preset release-native`

- Or the debug build

    - `cmake --workflow --preset debug-native`

- Run the following to view other presets available

    - `cmake --workflow --list-presets`

## Server

- After a successful build, the back-end peice of the application will be found here

    - `release/address_book_server`

    Or

    - `release-debug/address_book_server`

## Client

- After a successful build, the front-end peice of the application will be found here

    - `release/address_book_client`

    Or

    - `release-debug/address_book_client`