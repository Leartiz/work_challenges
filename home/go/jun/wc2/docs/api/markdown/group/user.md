<!-- User -->
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
    "people": [ 
        {
            "name": "<string>",
            "surname": "<string>",
            "patronymic": "<string>",
            "address": "<string>"
        },
        ...
    ]
}
```

<!-- --------------------------------------------------------------------- -->

# GET /api/account

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

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

# PUT /api/account

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

## Body
```json
{
    "name": "<string>", // optional
    "surname": "<string>", // optional
    "patronymic": "<string>", // optional
    "address": "<string>" // optional
}
```

## Responses
- 200

# DELETE /api/account

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

## Responses
- 200
  
