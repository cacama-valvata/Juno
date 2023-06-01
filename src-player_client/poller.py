import asyncio
import aiohttp
import aiomysql
import socket


async def get_dns_status(site):
    try:
        ip = await asyncio.get_event_loop().getaddrinfo(site, None)
        return ip[0][-1][0]
    except socket.gaierror:
        return "DNS Error"


async def get_http_status(site):
    async with aiohttp.ClientSession() as session:
        try:
            async with session.get(site) as response:
                return response.status
        except aiohttp.ClientConnectorError:
            return "HTTP Error"


async def execute_sql_query(host, port, query, user, password, db):
    pool = await aiomysql.create_pool(host,host,host,password,db)
    async with pool.acquire() as conn:
        async with conn.cursor() as cur:
            await cur.execute(query)
            results = await cur.fetchall()
            return results
        
async def process_file(file_path):
    with open(file_path, 'r') as file:
        for line in file:
            # Remove leading/trailing whitespace and split words by commas
            words = line.strip().split(',')
        
            if words[0] == "dns":
                dns_status = await get_dns_status(words[1])
                print(f"DNS Status: {dns_status}")
            
            elif words[0] == "http":
                http_status = await get_http_status(words[1])
                print(f"HTTP Status: {http_status}")

            elif words[0] == "sql":
                sql_query_results = await execute_sql_query(words[1],words[2],words[3],words[4],words[5],words[6])
                print(f"SQL Query Results: {sql_query_results}")

            else:
                print(f"Function '{words[0]}' does not exist.")

async def main():
    file_path = 'data.txt'  # Replace with your file path
    await process_file(file_path)

asyncio.run(main())
