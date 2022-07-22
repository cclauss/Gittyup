declare -a branches=("origin/context_line_accessor´" "origin/blame_abort" "origin/callback_connect_disconnect" "origin/disableRenameDetection" "origin/checkout_deletion_notification" "origin/blame_buffer" "origin/hash" "origin/disable_mmap" "origin/diff_checkout" "origin/fetch_annotated_tags")

for branch in ${branches[@]}; do
	git checkout $branch
	git rebase upstream/main
done

git checkout Gittyup
git reset --hard upstream/main

for branch in ${branches[@]}; do
	git merge --no-edit $branch
done
#git checkout Gittyup
#git reset --hard upstream/main
#git merge --no-edit "origin/context_line_accessor´"
#git merge --no-edit "origin/blame_abort"
#git merge --no-edit "origin/callback_connect_disconnect"
#git merge --no-edit "origin/disableRenameDetection"
#git merge --no-edit "origin/checkout_deletion_notification"
#git merge --no-edit "origin/blame_buffer"
#git merge --no-edit "origin/hash"
#git merge --no-edit "origin/disable_mmap"
#git merge --no-edit "origin/diff_checkout"
#git merge --no-edit "origin/fetch_annotated_tags"