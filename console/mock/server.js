import chalk from 'chalk';
import dns from 'dns';
import jsonServer from 'json-server';
import os from 'os';
import path from 'path';

const serverPort = process.env.SERVER_PORT ?? 8100;
const database = path.resolve('./mock/db.json');

const server = jsonServer.create();
const router = jsonServer.router(database);
const middlewares = jsonServer.defaults();

server.use(middlewares);

server.get('/api/scan', (req, res) => {
  res.json(['BatLAN', 'Free Wi-Fi']);
});

server.get('/api/status', (req, res) => {
  console.log(req.headers);
  res.json({ wifiConnected: true });
});

server.use(router);

server.listen(serverPort, () =>
  dns.lookup(os.hostname(), (err, add) => {
    console.log(chalk.bold('Mock server is running\n'));
    console.log(chalk.dim('Database:', chalk.cyan(database)));
    console.log(chalk.dim('Local:'), `http://localhost:${serverPort}`);
    console.log(chalk.dim('Network:'), `http://${add}:${serverPort}\n`);
  })
);
