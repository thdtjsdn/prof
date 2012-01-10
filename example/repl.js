var repl = require('../index').repl;

// Creates the Repl without any customizations
repl.createRepl();

// Use that PID to start debug server with: kill -31 <PID>
console.log('PID: %d', process.pid);

  // Keeps the process running
setInterval(function() {
  console.log('alive');
}, 10000);
