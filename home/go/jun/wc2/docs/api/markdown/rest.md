# Errors

- 400
```Txt
Bad request
```

- 500
```Txt
Internal server error
```

<!-- From Swagger Task -->
<!-- --------------------------------------------------------------------- -->

# GET /info

> People info

## Params

| Name | Type | Required |
| ---- | ---- | -------- |
| passportSeries | integer | true |
| passportNumber | integer | true |

## Responses
- 200
```json
{
    "name": "<string>",
    "surname": "<string>",
    "patronymic": "<string>",
    "address": "<string>"
}
```

<!-- --------------------------------------------------------------------- -->

# GET /api/user 

> People info

## Params

| Name | Type | Required |
| ---- | ---- | -------- |
| passportSeries | integer | false |
| passportNumber | integer | false |
| name | string | false |
| surname | string | false |
| patronymic | string | false |
| address | string | false |
| | | |
| limit | integer | false |
| offset | integer | false |

## Responses
- 200
```json
{
    "name": "<string>",
    "surname": "<string>",
    "patronymic": "<string>",
    "address": "<string>"
}
```

<!-- Auth -->
<!-- --------------------------------------------------------------------- -->

# POST /api/sign-up

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

# POST /api/refresh

## Body

```json
{
    "refreshToken": "<jwt-string>"
}
```

<!-- --------------------------------------------------------------------- -->

# PUT /api/user

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

## Body

```json
{
    "name": "<string>",
    "surname": "<string>",
    "patronymic": "<string>",
    "address": "<string>"
}
```

## Responses
- 200

# GET /api/user/{id}/task

## Params

|---|---|
|

# 