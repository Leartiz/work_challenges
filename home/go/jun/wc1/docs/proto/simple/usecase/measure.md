[<<](../descr.md)

# Measure

## GET /measure
> Get list of measurements

### Response
```json
[
  {
    "id": "<number>",
    "name": "<string>"
  },
  ...
]
```

## GET /measure/i
> Get information on the unit of measurement with identifier *i*

### Response
```json
[
  {
    "id": "<number>",
    "name": "<string>"
  },
  ...
]
```

## POST /measure
> Create a new unit of measure record

### Request
```json
{
  "name": "<string>"
}
```

### Response
```json
{
  "id": "<number>"
}
```

## PUT /measure/i
> Change unit record with identifier *i*

### Request
```json
{
  /* optional */
  "name": "<string>"
}
```

## DELETE /measure/i
> Delete a record of a unit of measure with identifier *i*