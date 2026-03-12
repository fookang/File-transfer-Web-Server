# File Transfer Server

A small HTTPS file transfer server written in C. It supports user registration/login, cookie-based sessions, and file uploads.

## Features

- **HTTPS Support**: TLS/SSL encryption using OpenSSL
- **User Authentication**: Registration and login with secure password hashing (PBKDF2-SHA256)
- **Session Management**: Cookie-based authentication with cryptographically secure random session tokens
- **File Upload**: Support for multipart/form-data file uploads
- **IPv4/IPv6 Support**: Dual-stack networking
- **Multiple Content Types**: Serves HTML, CSS, JavaScript, images, PDFs, and more

## Requirements

- GCC compiler
- OpenSSL development libraries
- Linux environment

## Installation

1. Clone or download the repository

2. Install dependencies (Ubuntu/Debian):

```bash
sudo apt-get install libssl-dev
```

3. Generate SSL certificates:

```bash
openssl req -x509 -newkey rsa:2048 -nodes -keyout key.pem -out cert.pem -days 365
```

> Note: the generated certificate is self-signed, so your browser will likely show a security warning when accessing `https://localhost:8080`.

4. Build the project:

```bash
make
```

## Usage

Start the server:

```bash
./file_transfer
```

The server will listen on port 8080. Access it via:

- `https://localhost:8080`

## Project Structure

```
├── Src/              # Source files
│   ├── file_transfer.c    # Main server implementation
│   └── client_info.c      # Client connection management
├── Inc/              # Header files
│   ├── client_info.h      # Client data structures
│   ├── users.h            # User authentication functions
│   └── cookie.h           # Session cookie management
├── Data/             # Persistent data storage
│   ├── users.txt          # User credentials
│   └── cookies.txt        # Active sessions
├── public/           # Web content
│   ├── *.html             # Public pages (login, register, home)
├── Makefile          # Build configuration
└── README.md         # This file
```

## Routes

- `GET /` - Home page
- `GET /login.html` - Login page
- `POST /login` - User login
- `GET /register.html` - Registration page
- `POST /register` - User registration
- `POST /upload` - File upload (authenticated)

## Security Features

- Password hashing with PBKDF2-SHA256 (10,000 iterations)
- 16-byte cryptographic salt per user
- 256-byte random session tokens, stored as 512-character hex cookies
- HTTPS/TLS encryption for all communications
- Session-based authentication

## Development

Clean build artifacts:

```bash
make clean
```

Rebuild from scratch:

```bash
make re
```

## Notes

- Default port: 8080
- User data persists in `Data/users.txt`
- Active sessions stored in `Data/cookies.txt`
