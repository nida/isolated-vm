if (process.versions.modules < 72) {
	console.log('pass');
	process.exit();
}
const ivm = require('isolated-vm');
const { Worker, isMainThread, parentPort } = require('worker_threads');
if (isMainThread) {
	const start = Date.now();
	const worker = new Worker(__filename);
	worker.on('message', () => { worker.terminate() });
	process.on('exit', () => {
		if (Date.now() - start < 1000) {
			console.log('pass');
		} else {
			console.log('fail');
		}
	});
} else {
	const isolate = new ivm.Isolate;
	const context = isolate.createContextSync();
	context.eval('for(;;);', { timeout: 5000 });
	parentPort.postMessage('');
}
