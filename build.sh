echo "Deleting previous build..."
rm -R build
rm demo.apk
rm demo.apk.idsig


echo "Copying assets..."
cp -r ./assets/* ./android/Sources/assets

echo "Build Running..."
make push run

# echo "Moving temporary files to ./generated"
# mv demo.apk ./generated
# mv demo.apk.idsig ./generated

