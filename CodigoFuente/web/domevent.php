<?php
header("Content-Type: application/x-dom-event-stream");
while(true) {
    echo "Event: server-time\n";
    $time = time();
    echo "data: $time\n";
    echo "\n";
    flush();
    sleep(3);
}
?>