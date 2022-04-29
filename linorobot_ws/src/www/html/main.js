// ws://54.147.26.233:9090

var app = new Vue({
  el: "#app",
  // storing the state of the page
  data: {
    connected: false,
    ros: null,
    ws_address: "ws://127.0.0.1:9090",
    ws_index_key: 0,
    logs: [],
    loading: false,
    topic: null,
    message: null,
  },
  // helper methods to connect to ROS
  methods: {
    connect: function () {
      this.loading = true;
      this.ros = new ROSLIB.Ros({
        url: this.ws_address,
      });
      this.ros.on("connection", () => {
        this.logs.unshift(new Date().toTimeString() + " - Connected!");
        this.connected = true;
        this.loading = false;
      });
      this.ros.on("error", (error) => {
        this.logs.unshift(new Date().toTimeString() + ` - Error: ${error}`);
      });
      this.ros.on("close", () => {
        this.logs.unshift(new Date().toTimeString() + " - Disconnected!");
        this.connected = false;
        this.loading = false;
      });
    },
    disconnect: function () {
      this.ros.close();
    },
    setTopic: function () {
      this.topic = new ROSLIB.Topic({
        ros: this.ros,
        name: "/location_index",
        messageType: "std_msgs/Int16",
      });
    },
    send_message: function (x) {
      console.log(x);
      this.message = new ROSLIB.Message({
        data: parseInt(x),
      });
      this.setTopic();
      this.topic.publish(this.message);
    },
  },
  mounted() {},
});
