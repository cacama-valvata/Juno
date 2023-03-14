import asyncio
import aiohttp
import aiomysql
import socket


async def get_dns_status():
    try:
        ip = await asyncio.get_event_loop().getaddrinfo('www.google.com', None)
        return ip[0][-1][0]
    except socket.gaierror:
        return "DNS Error"


async def get_http_status():
    async with aiohttp.ClientSession() as session:
        try:
            async with session.get('https://www.google.com') as response:
                return response.status
        except aiohttp.ClientConnectorError:
            return "HTTP Error"


async def execute_sql_query(query):
    pool = await aiomysql.create_pool(host='localhost', port=3306,user='root', password='root',db='Juno')
    async with pool.acquire() as conn:
        async with conn.cursor() as cur:
            await cur.execute(query)
            results = await cur.fetchall()
            return results


async def main():
    dns_status = await get_dns_status()
    http_status = await get_http_status()
    #sql_query_results = await execute_sql_query('SELECT * FROM devices')
    print(f"DNS Status: {dns_status}")
    print(f"HTTP Status: {http_status}")
    #print(f"SQL Query Results: {sql_query_results}")


asyncio.run(main())
