import fse from 'fs-extra';

const logInfo = (message) => {
  console.log('\x1b[32m%s\x1b[0m', `INFO: ${message}`);
}

fse.removeSync('../device/data/static');
fse.copySync('index.device.html', '../device/data/static/device.html');
fse.copySync('dist/device.bundled.js', '../device/data/static/device.js');

logInfo('Files copied to device data directory\n');
