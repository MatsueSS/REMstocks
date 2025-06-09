import json
import os
from datetime import datetime

today_str = datetime.now().strftime("%d-%m-%Y")

cards = []

with open("../res/products1.json", "r", encoding="utf-8") as f:
    data = json.load(f)

for product in data.get("products", []):
    name = product.get("name", "")
    prices = product.get("prices", {})

    regular = prices.get("regular")
    discount = prices.get("discount")

    cards.append({
        "name": name,
        "price": regular,
        "sale": discount
    })

result = {
    "date": today_str,
    "cards": cards
}

with open("cards.json", "w", encoding="utf-8") as f:
    json.dump(result, f, ensure_ascii=False, indent=4)