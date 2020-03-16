echo "update translations..."
lupdate ./src/plugins/notification_plugin/notification_plugin.pro

echo "generate new translate resources files"
for file in $(dirname $0)/*/*.ts
do
	ts="*.ts"
	qm="*.qm"
	target=${file%.*}.qm
	echo ${target}
	echo "release $file $target"
	lrelease $file $target
done
echo "done"
