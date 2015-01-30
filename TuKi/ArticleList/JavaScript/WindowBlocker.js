function WindowBlocker () {
    this.element = window.document.createElement("div");
    this.element.style.position = "absolute";
    this.element.style.left = "0px";
    this.element.style.top = "0px";
    this.element.style.backgroundColor = "black";
    this.element.style.display = "none";
    this.element.style.opacity = "0.50";
    window.document.body.appendChild(this.element);

    this.resize();
}

WindowBlocker.prototype.block = function () {
    this.element.style.display = "block";
    this.element.style.zIndex = 3;
}

WindowBlocker.prototype.unblock = function () {
    this.element.style.display = "none";
    this.element.style.zIndex = -3;
}

WindowBlocker.prototype.resize = function () {
    var w = window,
        d = document,
        e = d.documentElement,
        g = d.getElementsByTagName('body')[0],
        width = w.innerWidth || e.clientWidth || g.clientWidth,
        height = w.innerHeight|| e.clientHeight|| g.clientHeight;

    this.element.style.height = height + "px";
    this.element.style.width = width + "px";
}