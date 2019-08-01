Dir.glob('*/Makefile').each do |path| 
  dir = path.split('/')[0..-2].join('/')
  Dir.chdir(dir) do
    system "make -j8"
  end
end