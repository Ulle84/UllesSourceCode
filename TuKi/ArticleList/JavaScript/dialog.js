var windowBlocker;

function testDialog() {
    alert("block");
    windowBlocker.block();

}

function init() {
    windowBlocker = new WindowBlocker();
}