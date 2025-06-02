#!/usr/bin/env python3

import requests
import json
import sys

# url = "https://5d.5ka.ru/api/catalog/v2/stores/5156/categories/251C17046/products?mode=delivery&include_restrict=true&limit=120"

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/138.0",
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "Accept-Language": "ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3",
    "Origin": "https://5d.5ka.ru",
    "Referer": "https://5d.5ka.ru/",
    "Connection": "keep-alive",
}

low = 1
high = 512
best_data = None

while low <= high:
    mid = (low + high) // 2
    url = f"https://5d.5ka.ru/api/catalog/v2/stores/5156/categories/251C17046/products?mode=delivery&include_restrict=true&limit={mid}"
    response = requests.get(url, headers=headers)

    if response.status_code == 422:
        high = mid
        continue

    print(response.status_code)

    if response.status_code != 200:
        sys.exit(1)

    new_data = response.json()
    products = new_data.get("products")

    if products is None:
        high = mid - 1
    else:
        if best_data is None:
            best_data = new_data
            low = mid + 1
            continue
        if len(products) == len(best_data.get("products")):
            break
        else:
            best_data = new_data
            low = mid + 1

if best_data:
    with open("../res/products.json", "w", encoding="utf-8") as f:
        json.dump(best_data, f, ensure_ascii=False, indent=2)

sys.exit(0)