# Group

- [Auth](./group/auth.md)
- [User](./group/user.md)
- [Task](./group/task.md)

# Common Error Responses

- 400
```Txt
Bad request
```

- 500
```Txt
Internal server error
```

<!-- From Swagger Challenge -->
<!-- -------------------------------------------- -->

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
