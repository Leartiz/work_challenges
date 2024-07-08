<!-- Task -->
<!-- -------------------------------------------- -->

# GET /api/task
> Tasks info.

## Params

| Name | Type | Required |
| ---- | ---- | -------- |
| passportSeries | integer | true |
| passportNumber | integer | true |
| beginTime | integer | false |
| endTime | integer | false |

## Responses
- 200
```json
{
    "tasks": [
        {
            "id": "<number>",
            "name": "<string>",
            "timeSpentMinutes": "<number>"
        },
        ...
    ]
}
```

<!-- -------------------------------------------- -->

# POST /api/task

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

## Body
```json
{
    "name": "<string>" 
}
```

## Responses
- 200
```json
{
    "id": "<number>"
}
```

# GET /api/task

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

## Params

| Name | Type | Required |
| ---- | ---- | -------- |
| beginTime | integer | false |
| endTime | integer | false |

## Responses
- 200
```json
{
    "tasks": [
        {
            "id": "<number>",
            "name": "<string>",
            "timeSpentMinutes": "<number>"
        },
        ...
    ]
}
```

<!-- -------------------------------------------- -->

# POST /api/task/{id}/start

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

## Responses
- 200

# POST /api/task/{id}/stop

## Header

| Name | Value |
| ---- | ----- | 
| Authorization | Bearer `<jwt-string>` |

## Responses
- 200