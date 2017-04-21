(define-module (player)
  #:export (init update collision))

  (define (init)
    (display "hello from player init"))

  (define (update)
    (display "hello from player update"))

  (define (collision)
    (display "collision from guile!"))
