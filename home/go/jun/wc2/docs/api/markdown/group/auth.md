<!-- Auth -->
<!-- -------------------------------------------- -->

# POST /api/sign-up
> Adding a new user.

## Body
```json
{
    "passportNumber": "<number:4> <number:6>" 
}
```

## Responses
- 200
```json
{
    "accessToken": "<jwt-string>",
    "refreshToken": "<jwt-string>"
}
```

# POST /api/sign-in
## Body
```json
{
    "passportNumber": "<number:4> <number:6>",
    "password": "<string>"
}
```

## Responses
- 200
```json
{
    "accessToken": "<jwt-string>",
    "refreshToken": "<jwt-string>"
}
```

<!-- -------------------------------------------- -->

# POST /api/refresh
## Body
```json
{
    "refreshToken": "<jwt-string>"
}
```

## Responses
- 200
```json
{
    "accessToken": "<jwt-string>",
    "refreshToken": "<jwt-string>"
}
```

