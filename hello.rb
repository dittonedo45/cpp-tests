def rec(a)
  DIR["#{a}/*"].each do
    |x|
    begin
      (yield "#{a}/#{x}") if (fun "#{a}/#{x}")
    rescue => e
    end
  end
end

rec("..") do
  |x|
  p x
end
