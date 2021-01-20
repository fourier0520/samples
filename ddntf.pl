open(IN, "<test.html");
@data = <IN>;
close(IN);
$data = join("", split(/\n/, join("", @data)));
@arr = split(/<\/?div>/, $data);
foreach $line (@arr) {
    if ($line =~ /^\s*$/) {
        next;
    }
    if (!($line =~ /^\[メイン\]/)) {
        if ($line =~ /^\[.+\](.+)/) {
            print "<div>" . $1 . "</div>\n";
        }
    }
}
