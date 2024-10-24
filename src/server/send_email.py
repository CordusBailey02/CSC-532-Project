from mailersend import emails

api_key = "API_KEY"

mailer = emails.NewEmail(api_key)

# define an empty dict to populate with mail values
mail_body = {}

mail_from = {
    "name": "StackExchange Demake Project",
    "email": "info@stackexchangemail.me",
}

recipients = [
    {
        "name": "Cordus",
        "email": "ceb089@email.latech.edu",
    }
]

reply_to = [
    {
        "name": "StackExchange Demake Reply",
        "email": "reply@stackexchangemail.me",
    }
]

mailer.set_mail_from(mail_from, mail_body)
mailer.set_mail_to(recipients, mail_body)
mailer.set_subject("Hello!", mail_body)
mailer.set_html_content("This is the HTML content", mail_body)
mailer.set_plaintext_content("This is the text content", mail_body)
mailer.set_reply_to(reply_to, mail_body)

# using print() will also return status code and data
mailer.send(mail_body)