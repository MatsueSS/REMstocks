import requests
import json
import sys

headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:138.0) Gecko/20100101 Firefox/138.0',
    'Accept': 'application/json, text/plain, */*',
    'Accept-Language': 'ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3',
    'Accept-Encoding': 'gzip, deflate, br, zstd',
    'X-DEVICE-ID': '085d2704-2206-4623-8cad-a7a90341c7d9',
    'X-APP-VERSION': '0.1.1.dev',
    'X-PLATFORM': 'webapp',
    'Origin': 'https://5ka.ru',
    'DNT': '1',
    'Sec-GPC': '1',
    'Connection': 'keep-alive',
    'Sec-Fetch-Dest': 'empty',
    'Sec-Fetch-Mode': 'cors',
    'Sec-Fetch-Site': 'same-site',
    'TE': 'trailers',
    "Cookie": "_ym_uid=1737912662159805065; _ym_d=1737912662; spid=1737914675238_cab5604e9431ccd962b3e476066690b6_cjgc7ef7v633fsfp; spsc=1739679048239_e46af682ccdc8c4c596f94a222c44636_e6cfb3ea8f0a0fa28cc6ebefdcae8ea5; spid=1746713365382_9da291ae0277c1bd32ce244cb66e4307_21u1mqfci72dqjnx; spjs=1748939744191_207b82d8_0134ff91_a96d3c0c125f2fef9cf3ccda04f500e6_a8hIROu/L1oCt2YQSX8mqKEZA4/G+4hVHiJSX5f7UcD4WP3JImY2R0svT0RcFWGY5Qqv9l/zw82Nh9WxivMdyIGVZAJIxFSo8U2d4jqJOnaKbPnNVMXgMWo+Dj7TZyDMEWzZ9S6Hl3s3zluFmExNyfEVpRFJ/K/6DKD1SJUpa_qMqk2Qf369E8Be6CyxIkpIXXY8JWYKEl12-QxLe4eH0Z; TS01658276=01a2d8bbf452251b7e97b95156dcef5d9da625e9865816d46e0a46bc19bea6b701650d2500704705dfffd6ddc22b65e62c04f3b2bd6c107fcd13704c079c96ac5d736e0f7bae212056950d59d7f571dd8cdcc891e199722ca81dc20d431878a03606f1007173a7923b71505db7cdf66597e17f849a; SRV=4426d988-a5ab-4ce8-82b1-0791112255e2; TS018c7dc5=01a2d8bbf444d89fc47df88ed886980b986b34a321d371d36927b417eef4bff2dca9348a1074f8abf9ed3f04c3f4d0bec4f60aa8f1e7b8981189220d7d7eb755f8884d1707; _ym_isad=1; _ym_visorc=b",
}

url = "https://5d.5ka.ru/api/catalog/v2/stores/5156/categories/251C17046/products?mode=delivery&include_restrict=true&limit=400"

response = requests.get(url, headers=headers)

if(response.status_code == 403):
    sys.exit(1)

new_data = response.json()

with open("../res/products.json", "w", encoding="utf-8") as f:
    json.dump(new_data, f, ensure_ascii=False, indent=2)

sys.exit(0)

