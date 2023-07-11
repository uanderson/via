import proxy from 'koa-proxies';

export default {
  appIndex: 'index.dev.html',
  port: 8000,
  middleware: [
    proxy('/api', {
      target: 'http://localhost:8100',
    }),
  ],
  nodeResolve: true,
  open: true,
};
