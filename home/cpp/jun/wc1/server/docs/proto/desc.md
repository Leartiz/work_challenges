# Protocol over TCP 🧬

## Packet

### Header

- Длина тела. 4 байта, uint32, big endian.

### Body

- Строка в формате JSON.

<!-- -------------------------------------------- -->

## Math (calculate expression)

### Request

```json
{
    "request_id": "<uint64>",

    "service": "math",
    "action": "calculate",

    "payload": {
        "expression": "<string>"
    }
}
```

#### Example

```json
{
    "request_id": 12345678901234567890,

    "service": "math",
    "action": "calculate",

    "payload": {
        "expression": "3 + 5 * (2 - 8)"
    }
}
```

### Response

```json
{
    "request_id": "<uint64>",
    "status_code": "<HTTP status code>",

    // or
    "result": "<float64>",
    "error": {
        "message": "<string>"
    },

    // always
    "metadata": {
        "timestamp": "<timestamp as string>",
        "duration": "<duration as string>"
    }
}
```

#### Example

##### OK ✅

```json
{
    "request_id": 12345678901234567890,
    "status_code": 200,

    "result": 7.0,
    "error": null,

    "metadata": {
        "timestamp": "2024-12-15T15:30:01Z",
        "duration": "35ms"
    }
}
```

##### Error ❌

```json
{
    "request_id": 12345678901234567890,
    "status_code": 400,

    "result": null,
    "error": {
        "message": "invalid mathematical expression"
    },

    "metadata": {
        "timestamp": "2024-12-15T15:30:01Z",
        "duration": "5ms"
    }
}
```

<!-- -------------------------------------------- -->