(display "my-age --> ")
(display my-age)
(newline)

(display "my-height --> ")
(display my-height)
(newline)

(display "my-weight --> ")
(display my-weight)
(newline)


(define x 1)

(define do-hello
  (lambda ()
    (display "hello!")
    (display " x is: ")
    (display x)
    (newline)
    (set! x (+ x 1))))
