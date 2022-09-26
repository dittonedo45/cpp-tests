def rec(a)
  Dir["#{a}/*"].each do
    |x|
    begin
      (yield "#{x}") if (fun "#{x}")
    rescue => e
      p e
      next
    end
  end
end

rec("..") do
  |x|
  next if (File.exists? "#{x}/.git") and (File.file? "#{x}/.git")
  ((Dir["#{x}/.git/refs/remotes/*/*"].map {|x| File.basename x}) &
   (Dir["#{x}/.git/refs/heads/*"].map {|x| File.basename x})).each do
    |y|
    if not (File.read "#{x}/.git/refs/remotes/origin/#{y}")==
        (File.read "#{x}/.git/refs/heads/#{y}") then
    puts "--"
    end
  end
  #//p (File.realpath x)
end
