
(cl:in-package :asdf)

(defsystem "demo_server_client-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "add" :depends-on ("_package_add"))
    (:file "_package_add" :depends-on ("_package"))
  ))