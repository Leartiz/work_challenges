[<<](../descr.md)

# Product

## GET /product
> Get product list

### Response
```json
[
  {
    "id": "<number>",
    "name": "<string>",
    "quantity": "<number>",
    "unit_coast": "<number>",
    "measure": "<number>"
  },
  ...
]
```

## GET /product/i
> Get information on a product with identifier *i*

### Response
```json
{
  "id": "<number>",
  "name": "<string>",
  "quantity": "<number>",
  "unit_coast": "<number>",
  "measure": "<number>"
}
```

## POST /product
> Create a new product entry

### Request
```json
{
  "name": "<string>",
  "quantity": "<number>",
  "unit_coast": "<number>",
  "measure": "<number>"
}
```

### Response
```json
{
  "id": "<number>",
}
```

## PUT /product/i
> Change product record with identifier *i*

### Request
```json
{
  /* optional */
  "name": "<string>",
  "quantity": "<number>",
  "unit_coast": "<number>",
  "measure": "<number>"
}
```

## DELETE /product/i
> Delete a product record with identifier *i*